﻿using System;
using NUnit.Framework;

namespace ElectionGuard.Tests
{
    [TestFixture]
    public class TestEncrypt
    {
        string manifest = "{\"spec_version\":\"v0.95\",\"geopolitical_units\":[{\"object_id\":\"jefferson-county\",\"name\":\"Jefferson County\",\"type\":\"county\",\"contact_information\":{\"address_line\":[\"1234 Samuel Adams Way\",\"Jefferson, Hamilton 999999\"],\"name\":\"Jefferson County Clerk\",\"email\":[{\"annotation\":\"inquiries\",\"value\":\"inquiries@jefferson.hamilton.state.gov\"}],\"phone\":[{\"annotation\":\"domestic\",\"value\":\"123-456-7890\"}]}},{\"object_id\":\"harrison-township\",\"name\":\"Harrison Township\",\"type\":\"township\",\"contact_information\":{\"address_line\":[\"1234 Thorton Drive\",\"Harrison, Hamilton 999999\"],\"name\":\"Harrison Town Hall\",\"email\":[{\"annotation\":\"inquiries\",\"value\":\"inquiries@harrison.hamilton.state.gov\"}],\"phone\":[{\"annotation\":\"domestic\",\"value\":\"123-456-7890\"}]}},{\"object_id\":\"harrison-township-precinct-east\",\"name\":\"Harrison Township Precinct\",\"type\":\"township\",\"contact_information\":{\"address_line\":[\"1234 Thorton Drive\",\"Harrison, Hamilton 999999\"],\"name\":\"Harrison Town Hall\",\"email\":[{\"annotation\":\"inquiries\",\"value\":\"inquiries@harrison.hamilton.state.gov\"}],\"phone\":[{\"annotation\":\"domestic\",\"value\":\"123-456-7890\"}]}},{\"object_id\":\"rutledge-elementary\",\"name\":\"Rutledge Elementary School district\",\"type\":\"school\",\"contact_information\":{\"address_line\":[\"1234 Wolcott Parkway\",\"Harrison, Hamilton 999999\"],\"name\":\"Rutledge Elementary School\",\"email\":[{\"annotation\":\"inquiries\",\"value\":\"inquiries@harrison.hamilton.state.gov\"}],\"phone\":[{\"annotation\":\"domestic\",\"value\":\"123-456-7890\"}]}}],\"parties\":[{\"object_id\":\"whig\",\"abbreviation\":\"WHI\",\"color\":\"AAAAAA\",\"logo_uri\":\"http://some/path/to/whig.svg\",\"name\":{\"text\":[{\"value\":\"Whig Party\",\"language\":\"en\"}]}},{\"object_id\":\"federalist\",\"abbreviation\":\"FED\",\"color\":\"CCCCCC\",\"logo_uri\":\"http://some/path/to/federalist.svg\",\"name\":{\"text\":[{\"value\":\"Federalist Party\",\"language\":\"en\"}]}},{\"object_id\":\"democratic-republican\",\"abbreviation\":\"DEMREP\",\"color\":\"EEEEEE\",\"logo_uri\":\"http://some/path/to/democratic-repulbican.svg\",\"name\":{\"text\":[{\"value\":\"Democratic Republican Party\",\"language\":\"en\"}]}}],\"candidates\":[{\"object_id\":\"benjamin-franklin\",\"name\":{\"text\":[{\"value\":\"Benjamin Franklin\",\"language\":\"en\"}]},\"party_id\":\"whig\"},{\"object_id\":\"john-adams\",\"name\":{\"text\":[{\"value\":\"John Adams\",\"language\":\"en\"}]},\"party_id\":\"federalist\"},{\"object_id\":\"john-hancock\",\"name\":{\"text\":[{\"value\":\"John Hancock\",\"language\":\"en\"}]},\"party_id\":\"democratic-republican\"},{\"object_id\":\"write-in\",\"name\":{\"text\":[{\"value\":\"Write In Candidate\",\"language\":\"en\"},{\"value\":\"Escribir en la candidata\",\"language\":\"es\"}]},\"is_write_in\":true},{\"object_id\":\"referendum-pineapple-affirmative\",\"name\":{\"text\":[{\"value\":\"Pineapple should be banned on pizza\",\"language\":\"en\"}]}},{\"object_id\":\"referendum-pineapple-negative\",\"name\":{\"text\":[{\"value\":\"Pineapple should not be banned on pizza\",\"language\":\"en\"}]}}],\"contests\":[{\"@type\":\"CandidateContest\",\"object_id\":\"justice-supreme-court\",\"sequence_order\":0,\"ballot_selections\":[{\"object_id\":\"john-adams-selection\",\"sequence_order\":0,\"candidate_id\":\"john-adams\"},{\"object_id\":\"benjamin-franklin-selection\",\"sequence_order\":1,\"candidate_id\":\"benjamin-franklin\"},{\"object_id\":\"john-hancock-selection\",\"sequence_order\":2,\"candidate_id\":\"john-hancock\"},{\"object_id\":\"write-in-selection\",\"sequence_order\":3,\"candidate_id\":\"write-in\"}],\"ballot_title\":{\"text\":[{\"value\":\"Justice of the Supreme Court\",\"language\":\"en\"},{\"value\":\"Juez de la corte suprema\",\"language\":\"es\"}]},\"ballot_subtitle\":{\"text\":[{\"value\":\"Please choose up to two candidates\",\"language\":\"en\"},{\"value\":\"Uno\",\"language\":\"es\"}]},\"vote_variation\":\"n_of_m\",\"electoral_district_id\":\"jefferson-county\",\"name\":\"Justice of the Supreme Court\",\"primary_party_ids\":[\"whig\",\"federalist\"],\"number_elected\":2,\"votes_allowed\":2},{\"@type\":\"ReferendumContest\",\"object_id\":\"referendum-pineapple\",\"sequence_order\":1,\"ballot_selections\":[{\"object_id\":\"referendum-pineapple-affirmative-selection\",\"sequence_order\":0,\"candidate_id\":\"referendum-pineapple-affirmative\"},{\"object_id\":\"referendum-pineapple-negative-selection\",\"sequence_order\":1,\"candidate_id\":\"referendum-pineapple-negative\"}],\"ballot_title\":{\"text\":[{\"value\":\"Should pineapple be banned on pizza?\",\"language\":\"en\"},{\"value\":\"¿Debería prohibirse la piña en la pizza?\",\"language\":\"es\"}]},\"ballot_subtitle\":{\"text\":[{\"value\":\"The township considers this issue to be very important\",\"language\":\"en\"},{\"value\":\"El municipio considera que esta cuestión es muy importante\",\"language\":\"es\"}]},\"vote_variation\":\"one_of_m\",\"electoral_district_id\":\"harrison-township\",\"name\":\"The Pineapple Question\",\"number_elected\":1,\"votes_allowed\":1}],\"ballot_styles\":[{\"object_id\":\"jefferson-county-ballot-style\",\"geopolitical_unit_ids\":[\"jefferson-county\"]},{\"object_id\":\"harrison-township-ballot-style\",\"geopolitical_unit_ids\":[\"jefferson-county\",\"harrison-township\"]},{\"object_id\":\"harrison-township-precinct-east-ballot-style\",\"geopolitical_unit_ids\":[\"jefferson-county\",\"harrison-township\",\"harrison-township-precinct-east\",\"rutledge-elementary\"]},{\"object_id\":\"rutledge-elementary-ballot-style\",\"geopolitical_unit_ids\":[\"jefferson-county\",\"harrison-township\",\"rutledge-elementary\"]}],\"name\":{\"text\":[{\"value\":\"Jefferson County Spring Primary\",\"language\":\"en\"},{\"value\":\"Primaria de primavera del condado de Jefferson\",\"language\":\"es\"}]},\"contact_information\":{\"address_line\":[\"1234 Paul Revere Run\",\"Jefferson, Hamilton 999999\"],\"name\":\"Hamilton State Election Commission\",\"email\":[{\"annotation\":\"press\",\"value\":\"inquiries@hamilton.state.gov\"},{\"annotation\":\"federal\",\"value\":\"commissioner@hamilton.state.gov\"}],\"phone\":[{\"annotation\":\"domestic\",\"value\":\"123-456-7890\"},{\"annotation\":\"international\",\"value\":\"+1-123-456-7890\"}]},\"start_date\":\"2020-03-01T08:00:00-05:00\",\"end_date\":\"2020-03-01T20:00:00-05:00\",\"election_scope_id\":\"jefferson-county-primary\",\"type\":\"primary\"}";
        readonly string plaintext = "{\"object_id\":\"some-external-id-string-123\",\"ballot_style\":\"jefferson-county-ballot-style\",\"contests\":[{\"object_id\":\"justice-supreme-court\",\"ballot_selections\":[{\"object_id\":\"john-adams-selection\",\"vote\":1},{\"object_id\":\"write-in-selection\",\"vote\":1,\"extra_data\":\"some writein value\"}]}]}";
        [Test]
        public void test_Compact_Encrypt_Ballot_Simple_Succeeds()
        {
            var keypair = ElGamalKeyPair.FromSecret(Constants.TWO_MOD_Q);
            var description = new ElectionDescription(manifest);
            var metadata = new InternalElectionDescription(description);
            var context = new CiphertextElectionContext(1UL, 1UL, keypair.PublicKey, Constants.TWO_MOD_Q, metadata.DescriptionHash);
            var device = new EncryptionDevice(12345UL, 23456UL, 34567UL, "Location");
            var mediator = new EncryptionMediator(metadata, context, device);

            var ballot = new PlaintextBallot(plaintext);

            // Act
            var compact = mediator.CompactEncrypt(ballot);

            // Assert
            Assert.That(compact.ObjectId == ballot.ObjectId);

            var msgpack = compact.ToMsgPack();
            var fromMsgpack = new CompactCiphertextBallot(msgpack);

            Assert.That(compact.ObjectId == fromMsgpack.ObjectId);

        }
    }
}
